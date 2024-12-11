// src/app/page.tsx
import Link from 'next/link'

export default function Home() {
  return (
    <main className="min-h-screen flex flex-col items-center justify-center bg-gray-50">
      <h1 className="text-4xl font-bold mb-8">Game Engine</h1>
      <Link 
        href="/Documentation/index.html" 
        className="text-blue-600 hover:text-blue-800 underline"
      >
        View Documentation
      </Link>
    </main>
  )
}